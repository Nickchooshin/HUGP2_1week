using UnityEngine;
using System.Collections;

public class Enemy2_2 : MonoBehaviour
{
	Transform _transform;
	public AudioClip _sound;
	
	public float moveSpeed;

	void Start ()
	{
		moveSpeed = 3000.0f / 1.0f;
		_transform = GetComponent<Transform> ();

		GetComponent<AudioSource> ().clip = _sound;
		GetComponent<AudioSource> ().volume = 0.1f;
		GetComponent<AudioSource> ().Play ();
	}

	void FixedUpdate ()
	{
		Move ();
	}

	void Move()
	{
		Vector3 dir = new Vector3 (1.0f, 0.0f, 0.0f);
		
		_transform.localPosition += dir * (moveSpeed * Time.fixedDeltaTime);

		if (_transform.localPosition.x > 640.0f)
			_transform.localPosition = new Vector3 (-640.0f, _transform.localPosition.y, 0.0f);
	}
}