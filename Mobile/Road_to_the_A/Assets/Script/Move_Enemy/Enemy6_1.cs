using UnityEngine;
using System.Collections;

public class Enemy6_1 : MonoBehaviour
{
	Transform _transform;

	public float moveSpeed;
	public bool dir_check = false; // false : left, true : right

	void Start ()
	{
		moveSpeed = 400.0f / 1.0f;

		_transform = GetComponent<Transform> ();
	}

	void FixedUpdate ()
	{
		Move ();
	}

	void Move()
	{
		Vector3 _dir = Vector3.zero;

		// Select Direction
		if (_transform.transform.localPosition.x < -640.0f)
			dir_check = true;
		else if( _transform.transform.localPosition.x > 640.0f )
			dir_check = false;

		if( false == dir_check )
			_dir = new Vector3(-1.0f, 0.0f, 0.0f);
		else
			_dir = new Vector3(1.0f, 0.0f, 0.0f);

		_transform.transform.localPosition += _dir * (moveSpeed * Time.fixedDeltaTime);
	}
}