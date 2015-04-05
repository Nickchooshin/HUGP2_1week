using UnityEngine;
using System.Collections;

public class Safe1_1 : MonoBehaviour
{
	Transform _transform;
	public AudioClip _sound;

	void Start ()
	{
		_transform = GetComponent<Transform> ();

		GetComponent<AudioSource> ().clip = _sound;
		GetComponent<AudioSource> ().Play ();
	}

	void Update ()
	{
		
	}
}