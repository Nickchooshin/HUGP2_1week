using UnityEngine;
using System.Collections;

public class Warning : MonoBehaviour
{
	Transform _mytransform;
	Transform _transform;

	public bool chase_check = false;

	void Start ()
	{
		_mytransform = GetComponent<Transform> ();
		_transform = GameObject.FindGameObjectWithTag ("Player").transform;
	}

	void FixedUpdate ()
	{
		if( true == chase_check )
			Move_Character ();
	}

	void Move_Character()
	{
		Vector3 dir = Vector3.zero;
		dir = new Vector3 (_transform.position.x - _mytransform.position.x, 0.0f, 0.0f);
		//dir.Normalize ();

		_mytransform.position = _mytransform.position + dir;
	}
}