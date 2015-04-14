using UnityEngine;
using System.Collections;

public class Enemy1_3 : MonoBehaviour
{
	Transform _transform;
	public AudioClip[] _sound = new AudioClip[4];
	
	public float moveSpeed;
	public bool dir;
	public bool move;

	void Start ()
	{
		dir = false;	// false : left, true : right
		move = false;	// Move check
		moveSpeed = 100.0f / 1.0f;

		_transform = GetComponent<Transform> ();
	}

	void FixedUpdate ()
	{
		if( move == true )
		{
			if (dir == false)
				Left_Move ();
			else if (dir == true)
				Right_Move ();
		}
	}

	public void Left_Sound()
	{
		GetComponent<AudioSource> ().clip = _sound[0];
		GetComponent<AudioSource> ().Play ();
	}
	
	public void Right_Sound()
	{
		GetComponent<AudioSource> ().clip = _sound[1];
		GetComponent<AudioSource> ().Play ();
	}

	public void Stop_Sound()
	{
		GetComponent<AudioSource> ().clip = _sound[2];
		GetComponent<AudioSource> ().Play ();
	}
	
	public void Final_Sound()
	{
		GetComponent<AudioSource> ().clip = _sound[3];
		GetComponent<AudioSource> ().Play ();
	}

	void Left_Move()
	{
		Vector3 dir = new Vector3 (-1.0f, 0.0f, 0.0f);
		
		_transform.localPosition += dir * (moveSpeed * Time.fixedDeltaTime);
	}

	void Right_Move()
	{
		Vector3 dir = new Vector3 (1.0f, 0.0f, 0.0f);
		
		_transform.localPosition += dir * (moveSpeed * Time.fixedDeltaTime);
	}
}