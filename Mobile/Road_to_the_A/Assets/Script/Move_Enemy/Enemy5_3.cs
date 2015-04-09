using UnityEngine;
using System.Collections;

public class Enemy5_3 : MonoBehaviour
{
	Transform _transform;
	public AudioClip _sound;
	
	public float moveSpeed;
	
	void Start ()
	{
		moveSpeed = 800.0f / 1.0f;
		_transform = GetComponent<Transform> ();
		
		GetComponent<AudioSource> ().clip = _sound;
		GetComponent<AudioSource> ().Play ();
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