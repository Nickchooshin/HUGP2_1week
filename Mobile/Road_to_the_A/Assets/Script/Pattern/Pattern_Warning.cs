using UnityEngine;
using System.Collections;

public class Pattern_Warning : MonoBehaviour
{
	private GameObject obj_back;
	private GameObject obj_warning;

	void Start ()
	{
		// Back Object
		obj_back = Instantiate (Resources.Load ("Warning_back", typeof(GameObject))) as GameObject;
		obj_back.transform.parent = GameObject.Find ("Boss").transform;

		// Waning Object
		obj_warning = Instantiate (Resources.Load ("Warning_guide", typeof(GameObject))) as GameObject;
		obj_warning.transform.parent = GameObject.Find ("Boss").transform;
	}

	void FixedUpdate ()
	{

	}
	
	public void Setting (Vector3 _back, Vector3 _war, Vector3 _size_B, Vector3 _size_W)
	{
		// localPosition
		obj_back.transform.localPosition = _back;
		obj_back.transform.localPosition = _war;

		// size
		obj_back.transform.localScale = _size_B;
		obj_warning.transform.localScale = _size_W;
	}
}