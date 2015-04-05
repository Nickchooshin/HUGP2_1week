using UnityEngine;
using System.Collections;

public class Enemy1_1 : MonoBehaviour
{
	Transform _transform;
	public AudioClip _sound;

	public float moveSpeed;

	void Start ()
	{
		moveSpeed = 2160.0f / 0.5f;
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
		Vector3 dir = new Vector3 (0.0f, 1.0f, 0.0f);

		_transform.localPosition += dir * (moveSpeed * Time.fixedDeltaTime);
	}

	public void Destroy_obj()
	{
		Destroy (_transform.gameObject);
	}
}