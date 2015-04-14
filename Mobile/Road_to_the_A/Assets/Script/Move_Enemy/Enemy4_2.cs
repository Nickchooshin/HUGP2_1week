using UnityEngine;
using System.Collections;

public class Enemy4_2 : MonoBehaviour
{
	Transform _transform;
	
	public bool move_check;
	public float moveSpeed;
	public int dir_num = 0;
	public Vector3[] m_dir = new Vector3[3];
	
	void Start ()
	{
		moveSpeed = 500.0f / 1.0f;
		_transform = GetComponent<Transform> ();
	}
	
	void FixedUpdate ()
	{
		if( true == move_check )
			Move ();
	}
	
	void Move()
	{
		Vector3 dir = Vector3.zero;

		if( 0 == dir_num )
		{
			// 3방향 - 1
			dir = new Vector3(-630.0f, -300.0f, 0.0f);
		}
		else if( 1 == dir_num )
		{
			// 3방향 - 2
			dir = new Vector3(-220.0f, -300.0f, 0.0f);
		}
		else if( 2 == dir_num )
		{
			// 3방향 - 3
			dir = new Vector3(190.0f, -300.0f, 0.0f);
		}
		else if( 3 == dir_num )
		{
			// 2방향 - 1
			dir = new Vector3(-425.0f, -300.0f, 0.0f);
		}
		else if( 4 == dir_num )
		{
			// 2방향 - 2
			dir = new Vector3(-15.0f, -300.0f, 0.0f);
		}
		dir = dir - _transform.transform.position;
		dir.Normalize ();
		
		_transform.localPosition += dir * (moveSpeed * Time.fixedDeltaTime);
	}
}