using UnityEngine;
using System.Collections;

public class Enemy3_1 : MonoBehaviour
{
	Transform _mytransform;
	public Vector3 _finish;
	
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
		Vector3 _dir = _mytransform.transform.localPosition - _finish;
		_dir.Normalize ();

		_mytransform.transform.localPosition += _dir * (moveSpeed * Time.fixedDeltaTime);
	}
}