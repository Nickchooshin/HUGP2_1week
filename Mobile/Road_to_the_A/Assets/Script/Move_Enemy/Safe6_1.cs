using UnityEngine;
using System.Collections;

public class Safe6_1 : MonoBehaviour
{
	Transform _transform;

	float moveSpeed;

	void Start ()
	{
		moveSpeed = 630.0f / 2.0f;

		_transform = GetComponent<Transform> ();
	}

	void FixedUpdate ()
	{
		Move ();
	}

	void Move()
	{
		Vector3 _dir = new Vector3 (0.0f, 1.0f, 0.0f);

		if( _transform.transform.localPosition.y < -10 )
			_transform.transform.localPosition += _dir * (moveSpeed * Time.fixedDeltaTime);
	}
}