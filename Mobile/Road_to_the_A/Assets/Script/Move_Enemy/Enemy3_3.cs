using UnityEngine;
using System.Collections;

public class Enemy3_3 : MonoBehaviour
{
	Transform _transform;
	public AudioClip[] _sound = new AudioClip[2];

	public float moveSpeed;
	public bool move_dir = false;	// false : updown, true : side

	Vector3 dir;

	void Start ()
	{
		_transform = GetComponent<Transform> ();

		if( false == move_dir )
		{
			GetComponent<AudioSource> ().clip = _sound[0];
			GetComponent<AudioSource> ().Play ();

			moveSpeed = 1800.0f / 0.3f;
			dir = new Vector3(0.0f, 1.0f, 0.0f);
			dir.Normalize();
		}
		else
		{
			GetComponent<AudioSource> ().clip = _sound[1];
			GetComponent<AudioSource> ().Play ();

			moveSpeed = 1800.0f / 1.0f;
			dir = new Vector3(1.0f, 0.0f, 0.0f);
			dir.Normalize();
		}
	}

	void FixedUpdate () 
	{
		Move ();
	}

	void Move()
	{
		if( false == move_dir )
		{
			_transform.transform.localPosition += dir * (moveSpeed * Time.fixedDeltaTime);

			if( _transform.localPosition.y > -134.0f )
				dir = new Vector3(0.0f, -1.0f, 0.0f);
		}
		else
		{
			// 회전
			_transform.eulerAngles = new Vector3 (0, 0.0f, 90.0f);
			
			_transform.transform.localPosition += dir * (moveSpeed * Time.fixedDeltaTime);

			if( _transform.localPosition.x > 640.0f )
				dir = new Vector3(-1.0f, 0.0f, 0.0f);
		}
	}
}