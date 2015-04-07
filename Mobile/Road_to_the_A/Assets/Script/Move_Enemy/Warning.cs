using UnityEngine;
using System.Collections;

public class Warning : MonoBehaviour
{
	Transform _mytransform;
	Transform _transform;

	public bool chase_check = false;
	public bool move_check = false;
	private bool first;
	private float dis;

	void Start ()
	{
		first = false;
		dis = 200.0f;
		_mytransform = GetComponent<Transform> ();
		_transform = GameObject.FindGameObjectWithTag ("Player").transform;
	}

	void FixedUpdate ()
	{
		if( true == chase_check )
			Move_Character ();
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
		Vector3 dir = Vector3.zero;
		dir = new Vector3 (_transform.position.x - _mytransform.position.x, 0.0f, 0.0f);
		//dir.Normalize ();

		if (dir.x > 0.0f)
			move_check = true;

		if (true == move_check)
		{
			if( false == first )
			{
				if( dir.x < 0.0f )
					dis = -200.0f;
				else if( dir.x > 0.0f )
					dis = 200.0f;
			}
			_mytransform.localPosition += (  );
		}
	}
}