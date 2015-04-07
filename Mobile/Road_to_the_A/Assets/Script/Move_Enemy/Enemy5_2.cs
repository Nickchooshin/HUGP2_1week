using UnityEngine;
using System.Collections;

public class Enemy5_2 : MonoBehaviour
{
	Transform _transform;
	Vector3 _dir;

	public float moveSpeed;
	private bool dir_check;
	
	void Start ()
	{
		dir_check = false;
		moveSpeed = 350.0f / 0.3f;

		_dir = new Vector3 (0.0f, 1.0f, 0.0f);
		_transform = GetComponent<Transform> ();
	}
	
	void FixedUpdate ()
	{
		Move ();
	}
	
	void Move()
	{
		if( _transform.transform.localPosition.y > -310.0f )
			_dir = new Vector3 (0.0f, -1.0f, 0.0f);

		_transform.transform.localPosition += _dir * (moveSpeed * Time.fixedDeltaTime);
	}
}