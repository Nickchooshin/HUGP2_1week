using UnityEngine;
using System.Collections;

public class Move_Character : MonoBehaviour
{
	// transform
	Transform _transform;

	// move
	public float moveSpeed = 1.0f;
	bool direction = false;		// false : right, true : left

	// object size
	private float halfsize_x = 25.0f;
	private float halfsize_y = 45.0f;

	void Awake()
	{
		_transform = GetComponent<Transform> ();
	}

	void Update ()
	{
		Move_Process ();
	}

	void Move_Process()
	{
		Vector3 dir = Vector3.zero;

		if( direction == false )
		{
			dir = new Vector3(1, 0, 0);
			dir.Normalize ();

			_transform.position += dir * moveSpeed * Time.deltaTime;
		}
		else if( direction == true )
		{
			dir = new Vector3(-1, 0, 0);
			dir.Normalize ();
			
			_transform.position += dir * moveSpeed * Time.deltaTime;
		}

		// 이동 제한
		_transform.localPosition = new Vector3 (Mathf.Clamp (_transform.localPosition.x, -640.0f + halfsize_x, 640.0f - halfsize_x),
		                                        Mathf.Clamp (_transform.localPosition.y, -360.0f + halfsize_y, 360.0f - halfsize_y),
		                                        _transform.localPosition.z);
	}
}