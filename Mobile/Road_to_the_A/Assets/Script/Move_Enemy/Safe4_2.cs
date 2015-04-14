using UnityEngine;
using System.Collections;

public class Safe4_2 : MonoBehaviour
{
	Transform _transform;
	public AudioClip _sound;

	float move_speed;
	public bool move_check;
	public bool tri_check;

	void Start ()
	{
		tri_check = true;
		move_check = false;
		move_speed = 1200.0f / 1.0f;

		_transform = GetComponent<Transform> ();
	}
	
	void FixedUpdate ()
	{
		if( true == tri_check )
			Move ();
	}

	void Move()
	{
		Vector3 dir = new Vector3 (0.0f, -1.0f, 0.0f);

		if( false == move_check )
		{
			_transform.transform.localPosition += dir * (move_speed * Time.fixedDeltaTime);
		}
		else
		{
			move_speed = 40.0f / 0.5f;

			_transform.transform.localPosition += dir * (move_speed * Time.fixedDeltaTime);
		}
	}

	void OnTriggerEnter2D( Collider2D other )
	{
		if( other.tag == "Tile" )
		{
			tri_check = false;

			GetComponent<AudioSource> ().clip = _sound;
			GetComponent<AudioSource> ().Play ();
		}
	}
}