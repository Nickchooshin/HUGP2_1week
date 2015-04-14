using UnityEngine;
using System.Collections;

public class Enemy3_2 : MonoBehaviour
{
	Transform _transform;
	
	public float moveSpeed;
	
	void Start ()
	{
		moveSpeed = 500.0f / 1.0f;

		_transform = GetComponent<Transform> ();
	}
	
	void FixedUpdate ()
	{
		Move ();
	}
	
	public void Move()
	{
		Vector3 _dir = new Vector3(0.0f, -1.0f, 0.0f);
		_dir.Normalize ();
		
		_transform.transform.localPosition += _dir * (moveSpeed * Time.fixedDeltaTime);
	}
}