#include "cubic_bezier_splines.h"
#include <stdbool.h>
#include <windows.h>
#include <math.h>
#include <hard_assert.h>

struct cbs_spline
{   struct
    {   struct cbs_point * array;
        int length;
    } points;
    struct
    {   float spline;
        float * curves;
    } lengths;
};

struct curve_positions
{   struct
    {   struct cbs_vector2 position, offset;
    } origin, destination;
};

static float compute_distance_between_vectors(struct cbs_vector2, struct cbs_vector2);
static struct cbs_vector2 compute_linear_interpolation(struct cbs_vector2, struct cbs_vector2, float);
static struct cbs_vector2 compute_offset_position(struct cbs_point, bool invert);
static struct curve_positions compute_curve_positions(struct cbs_point * curve);

struct cbs_spline * cbs_load_spline(struct cbs_point points[], int points_length)
{   struct cbs_spline * spline = calloc(1, sizeof(struct cbs_spline));

    spline->points.array = points;
    spline->points.length = points_length;

    spline->lengths.curves = malloc(sizeof(float) * (points_length - 1));
    for(int i = 1; i < points_length; ++i)
    {   struct curve_positions curve_positions = compute_curve_positions(&points[i - 1]);

        // https://stackoverflow.com/a/37862545

        float control_net_length =
            compute_distance_between_vectors(curve_positions.origin.position, curve_positions.origin.offset) +
            compute_distance_between_vectors(curve_positions.origin.offset, curve_positions.destination.offset) +
            compute_distance_between_vectors(curve_positions.destination.offset, curve_positions.destination.position);

        float chord_length = compute_distance_between_vectors(curve_positions.origin.position, curve_positions.destination.position);

        float average = control_net_length + chord_length / 2;

        spline->lengths.curves[i - 1] = average;
        spline->lengths.spline += average;
    }

    return spline;
}

struct cbs_vector2 cbs_compute_position(float delta, struct cbs_spline * spline)
{	if(delta <= 0)
		return spline->points.array[0].position;
	if(delta >= spline->lengths.spline)
		return spline->points.array[spline->points.length - 1].position;
    float curve_destination_delta = 0, curve_origin_delta = 0;
	for(int i = 0; i < (spline->points.length - 1); ++i)
    {   curve_destination_delta += spline->lengths.curves[i];

		if(curve_destination_delta >= delta)
		{	struct curve_positions curve_positions = compute_curve_positions(&spline->points.array[i]);

			float curve_length = curve_destination_delta - curve_origin_delta;
            float curve_delta = delta - curve_origin_delta;
            float normalized_curve_delta = curve_delta / curve_length;

			struct cbs_vector2 first_pass[3] =
			{	compute_linear_interpolation(curve_positions.origin.position, curve_positions.origin.offset, normalized_curve_delta),
				compute_linear_interpolation(curve_positions.origin.offset, curve_positions.destination.offset, normalized_curve_delta),
				compute_linear_interpolation(curve_positions.destination.offset, curve_positions.destination.position, normalized_curve_delta)
			};

			struct cbs_vector2 second_pass[2] =
			{	compute_linear_interpolation(first_pass[0], first_pass[1], normalized_curve_delta),
				compute_linear_interpolation(first_pass[1], first_pass[2], normalized_curve_delta)
			};

			struct cbs_vector2 third_pass = compute_linear_interpolation(second_pass[0], second_pass[1], normalized_curve_delta);

			return third_pass;
		}

		curve_origin_delta = curve_destination_delta;
    }
	ha_abort("Cubic Bezier Splines", "Invalid spline passed for position computation.");
}

float cbs_get_spline_length(struct cbs_spline * spline)
{   return spline->lengths.spline;
}

void cbs_cleanup_spline(struct cbs_spline * spline)
{   free(spline->lengths.curves);
    free(spline);
}

static float compute_distance_between_vectors(struct cbs_vector2 vector1, struct cbs_vector2 vector2)
{   struct cbs_vector2 offset =
    {   .x = vector2.x - vector1.x,
        .y = vector2.y - vector1.y
    };
    return sqrt(pow(offset.x, 2) + pow(offset.y, 2));
}

static struct cbs_vector2 compute_linear_interpolation(struct cbs_vector2 origin, struct cbs_vector2 destination, float delta)
{	return (struct cbs_vector2)
	{	.x = origin.x + (destination.x - origin.x) * delta,
		.y = origin.y + (destination.y - origin.y) * delta
	};
}

static struct cbs_vector2 compute_offset_position(struct cbs_point point, bool invert)
{	int factor = invert ? -1 : 1;
    return (struct cbs_vector2)
	{	.x = point.position.x + point.influence_point_offset.x * factor,
		.y = point.position.y + point.influence_point_offset.y * factor
	};
}

static struct curve_positions compute_curve_positions(struct cbs_point * curve)
{   return (struct curve_positions)
    {   .origin =
        {   .position = curve[0].position,
            .offset = compute_offset_position(curve[0], true)
        },
        .destination =
        {   .position = curve[1].position,
            .offset = compute_offset_position(curve[1], false)
        },
    };
}
