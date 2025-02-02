
uniform mat4 cvfu_modelViewProjectionMatrix;

#ifdef CVF_CALC_CLIP_DISTANCES_IMPL
uniform mat4 cvfu_modelViewMatrix;
#endif

attribute vec4 cvfa_vertex;

//--------------------------------------------------------------------------------------------------
/// Vertex Shader - Minimal
//--------------------------------------------------------------------------------------------------
void main ()
{
	gl_Position = cvfu_modelViewProjectionMatrix*cvfa_vertex;

#ifdef CVF_CALC_CLIP_DISTANCES_IMPL
	vec3 ecPosition = (cvfu_modelViewMatrix * cvfa_vertex).xyz;
	calcClipDistances(vec4(ecPosition, 1));
#endif
}
