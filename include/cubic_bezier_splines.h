#pragma once

typedef enum { cbs_false, cbs_true } cbs_bool;

struct cbs_vector2
{	float x;
	float y;
};

struct cbs_point
{	struct cbs_vector2 position;
	struct cbs_vector2 influence_point_offset;
};

struct cbs_spline;

struct cbs_spline * cbs_load_spline(struct cbs_point points[], int points_length);
struct cbs_vector2 cbs_compute_position(float delta, struct cbs_spline *);
float cbs_get_spline_length(struct cbs_spline *);
void cbs_cleanup_spline(struct cbs_spline *);
