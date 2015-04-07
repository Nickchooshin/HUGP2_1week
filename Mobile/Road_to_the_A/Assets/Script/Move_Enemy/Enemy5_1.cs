using UnityEngine;
using System.Collections;

public class Enemy5_1 : MonoBehaviour
{
	Transform _transform;

	public float moveSpeed;
	
	void Start ()
	{
		moveSpeed = 600.0f / 1.0f;

		_transform = GetComponent<Transform> ();
	}
	
	void FixedUpdate ()
	{
		Move ();
	}
	
	void Move()
	{
		Vector3 dir = new Vector3 (0.0f, -1.0f, 0.0f);
		
		_transform.localPosition += dir * (moveSpeed * Time.fixedDeltaTime);
	}
}