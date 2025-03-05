# Types
API Types.

### cbs_bool
```c
typedef enum { cbs_false, cbs_true } cbs_bool;
```
**About** \
Exists solely for compatibility purposes. CBS uses `stdbool` under the hood.

<br/>

### cbs_vector2
```c
struct cbs_vector2
{	float x;
	float y;
};
```
**About** \
Used to represent 2-dimensional positions.

<br/>

### cbs_point
```c
struct cbs_point
{	struct cbs_vector2 position;
	struct cbs_vector2 influence_point_offset;
};

```
**About** \
Used to represent the positions of a spline point and its influence point.

<br/>

### cbs_spline
```c
struct cbs_spline;
```
**About** \
Undefined type used as a pointer to enact spline handles.