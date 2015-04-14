using UnityEngine;
using System.Collections;

public class Warning : MonoBehaviour
{
	Transform _mytransform;
	Transform _transform;

	public bool chase_check = false;
	public bool chaseA_check = false;
	private bool first;
	private Vector3 dis;
	public float speed;
	public float accel;

	void Start ()
	{
		first = false;
		speed = 0.0f;
		accel = 800.0f;
		dis = Vector3.zero;

		_mytransform = GetComponent<Transform> ();
		_transform = GameObject.FindGameObjectWithTag ("Player").transform;
	}

	void FixedUpdate ()
	{
		if( true == chase_check )
			Move_Character ();

		if (true == chaseA_check)
			Move_aCharacter ();
	}

	void Move_Character()
	{
		Vector3 dir = Vector3.zero;
		dir = new Vector3 (_transform.position.x - _mytransform.position.x, 0.0f, 0.0f);
		//dir.Normalize ();

		_mytransform.position = _mytransform.position + dir;
	}

	void Move_aCharacter()
	{
		Vector3 dir = new Vector3(1.0f, 0.0f, 0.0f);
		dir.Normalize ();

		_mytransform.localPosition += dir * (speed * Time.fixedDeltaTime);

		if( _transform.position.x - _mytransform.position.x > 0.0f )
			speed += (dir.x * (accel * Time.fixedDeltaTime));
		else if( _transform.position.x - _mytransform.position.x < 0.0f )
			speed -= (dir.x * (accel * Time.fixedDeltaTime));

		/*
		dir = new Vector3 (_transform.position.x - _mytransform.position.x, 0.0f, 0.0f);
		dir.Normalize ();
		Debug.Log (dir);
		
		_mytransform.localPosition += dir * (speed * Time.fixedDeltaTime);
		speed += (dir.x * (accel * Time.fixedDeltaTime));
		*/
	}
}