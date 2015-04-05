using UnityEngine;
using System.Collections;

public class Safe3_2 : MonoBehaviour
{
	Transform _transform;
	public AudioClip _sound;

	public bool move_check;
	float moveSpeed;

	void Start ()
	{
		moveSpeed = 300.0f / 1.0f;

		_transform = GetComponent<Transform> ();
		
		GetComponent<AudioSource> ().clip = _sound;
		GetComponent<AudioSource> ().Play ();
	}

	void FixedUpdate ()
	{
		if (true == move_check)
			Move ();
	}

	void Move()
	{
		Vector3 _dir = new Vector3 (0.0f, 1.0f, 0.0f);

		_transform.localPosition += _dir * (moveSpeed * Time.fixedDeltaTime);
	}
}