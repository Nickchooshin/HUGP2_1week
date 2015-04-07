using UnityEngine;
using System.Collections;

public class Enemy4_2 : MonoBehaviour
{
	Transform _transform;
	public AudioClip _sound;

	bool move_check;
	public float moveSpeed;
	public Vector3[] m_dir = new Vector3[3];
	
	void Start ()
	{
		moveSpeed = 2160.0f / 0.5f;
		_transform = GetComponent<Transform> ();
		
		GetComponent<AudioSource> ().clip = _sound;
		GetComponent<AudioSource> ().Play ();
	}
	
	void FixedUpdate ()
	{
		if( true == move_check )
			Move ();
	}
	
	void Move()
	{
		Vector3 dir = new Vector3 (0.0f, 1.0f, 0.0f);
		
		_transform.localPosition += dir * (moveSpeed * Time.fixedDeltaTime);
	}
}