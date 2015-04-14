using UnityEngine;
using System.Collections;

public class Enemy4_1 : MonoBehaviour
{
	Transform _transform;
	public AudioClip _sound;
	
	public float moveSpeed;
	public bool check;
	
	void Start ()
	{
		check = true;
		moveSpeed = 1000.0f / 1.0f;
		_transform = GetComponent<Transform> ();
	}
	
	void FixedUpdate ()
	{
		Move();
	}
	
	void Move()
	{
		Vector3 dir = new Vector3 (-1.0f, 0.0f, 0.0f);
		
		_transform.localPosition += dir * (moveSpeed * Time.fixedDeltaTime);
	}
}