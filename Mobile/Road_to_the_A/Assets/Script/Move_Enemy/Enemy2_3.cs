using UnityEngine;
using System.Collections;

public class Enemy2_3 : MonoBehaviour
{
	Transform _mytransform;
	Transform _transform;
	Vector3 _now;

	public float moveSpeed;
	public bool move_check;
	private bool dir_check;

	void Start ()
	{
		dir_check = false;
		move_check = false;
		moveSpeed = 500.0f / 1.0f;
		_mytransform = GetComponent<Transform> ();
	}

	void FixedUpdate ()
	{
		if (true == move_check)
			Move ();
	}

	public void Move()
	{
		if( false == dir_check )
		{
			_transform = GameObject.FindGameObjectWithTag("Player").transform;
			_now = _transform.transform.localPosition;
			dir_check = true;
		}

		Vector3 dir = _now - _mytransform.localPosition;
		dir.Normalize ();

		_mytransform.localPosition += dir * (moveSpeed * Time.fixedDeltaTime);
	}
}