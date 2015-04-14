using UnityEngine;
using System.Collections;

public class Enemy2_3 : MonoBehaviour
{
	Transform _mytransform;
	Transform _transform;
	Vector3 _now;
	Vector3 m_dir;
//	Ray2D r;

	public float moveSpeed;
	public bool move_check;
	private bool dir_check;

	void Start ()
	{
		dir_check = false;
		move_check = false;
		moveSpeed = 1000.0f / 1.0f;
//		r = Vector2.zero;

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
			m_dir = _now - _mytransform.localPosition;
			m_dir.Normalize ();

			dir_check = true;
		}

		_mytransform.localPosition += m_dir * (moveSpeed * Time.fixedDeltaTime);
	}

	void Make_ray()
	{
		if( false == dir_check )
		{
			_transform = GameObject.FindGameObjectWithTag("Player").transform;
			_now = _transform.transform.localPosition;
			m_dir = _now - _mytransform.localPosition;
			m_dir.Normalize ();
			
			dir_check = true;
		}

		
	}
}