using UnityEngine;
using System.Collections;

public class Safe5_1 : MonoBehaviour
{
	Transform _transform;
	public AudioClip _sound;

	private float moveSpeed;
	Vector3 _dir;
	
	void Start ()
	{
		moveSpeed = 400.0f / 1.0f;
		_dir = new Vector3 (-1.0f, 0.0f, 0.0f);

		_transform = GetComponent<Transform> ();
		
		GetComponent<AudioSource> ().clip = _sound;
		GetComponent<AudioSource> ().Play ();
	}
	
	void FixedUpdate ()
	{
		Move ();
	}

	void Move ()
	{
		StartCoroutine ("Move_Time");

		_transform.transform.localPosition += _dir * (moveSpeed * Time.fixedDeltaTime);
	}
	
	IEnumerator Move_Time()
	{
		yield return new WaitForSeconds(1.0f);

		_dir = Vector3.zero;
		yield return new WaitForSeconds(0.5f);

		_dir = new Vector3 (1.0f, 0.0f, 0.0f);
	}
}