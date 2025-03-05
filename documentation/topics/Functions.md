# Functions
API Functions.

### cbs_load_spline
```c
struct cbs_spline * cbs_load_spline(struct cbs_point points[], int points_length);
```
**points** \
Array of `cbs_point` representing a spline. \
\
**points_length** \
Amount of elements contained in the given **points** array. \
\
**Return Value** \
Valid spline handle to be used with other CBS functions. \
\
**About** \
Loads the given spline and returns a valid corresponding handle.

<br/>

### cbs_compute_position
```c
struct cbs_vector2 cbs_compute_position(float delta, struct cbs_spline *);
```
**delta** \
Cubic bezier delta value from 0 to the spline's length. Out-of-bounds values will be silently corrected by CBS. \
\
**\*Nameless Argument\*** \
Spline handle. \
\
**Return Value** \
Computed point position. \
\
**About** \
Computes the position of a point along a spline based on its delta value.

<br/>

### cbs_get_spline_length
```c
float cbs_get_spline_length(struct cbs_spline *);
```
**\*Nameless Argument\*** \
Spline handle. \
\
**Return Value** \
Spline length. \
\
**About** \
Fetches the length of a given spline.

<br/>

### cbs_cleanup_spline
```c
void cbs_cleanup_spline(struct cbs_spline *);
```
**\*Nameless Argument\*** \
Spline handle. \
\
**About** \
Cleans up internal CBS memory related to a spline. All splines loaded using `cbs_load_spline()` should eventually be passed to this function.