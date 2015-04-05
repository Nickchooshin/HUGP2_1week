using UnityEngine;
using System.Collections;

public class Enemy3_3 : MonoBehaviour
{
	Transform _transform;
	public AudioClip _sound;

	public float moveSpeed;
	public bool move_dir;	// false : down, true : up

	void Start ()
	{
		move_dir = false;
		moveSpeed = 1000.0f / 0.3f;
		
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
		if( false == move_dir )
		{
			Vector3 _dir = new Vector3(0.0f, -1.0f, 0.0f);
			_dir.Normalize ();
		
			_transform.transform.localPosition += _dir * (moveSpeed * Time.fixedDeltaTime);
		}
		else
		{
			Vector3 _dir = new Vector3(0.0f, 1.0f, 0.0f);
			_dir.Normalize ();
			
			_transform.transform.localPosition += _dir * (moveSpeed * Time.fixedDeltaTime);
		}
	}
}