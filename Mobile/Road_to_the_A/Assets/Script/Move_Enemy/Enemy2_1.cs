using UnityEngine;
using System.Collections;

public class Enemy2_1 : MonoBehaviour
{
	Transform _transform;
	public AudioClip _sound;

	public float moveSpeed;
	public bool check;

	void Start ()
	{
		check = true;
		moveSpeed = 600.0f / 1.0f;
		_transform = GetComponent<Transform> ();
	}

	void FixedUpdate ()
	{
		if( check == true )
			Move();
	}

	void Move()
	{
		Vector3 dir = new Vector3 (0.0f, -1.0f, 0.0f);
		
		_transform.localPosition += dir * (moveSpeed * Time.fixedDeltaTime);
	}

	void OnTriggerEnter2D( Collider2D other )
	{
		if( other.tag == "Tile" )
		{
			check = false;

			GetComponent<AudioSource> ().clip = _sound;
			GetComponent<AudioSource> ().Play ();
		}
	}
}