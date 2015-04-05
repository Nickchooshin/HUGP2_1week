using UnityEngine;
using System.Collections;

public class Move_Character : MonoBehaviour
{
	// transform
	Transform _transform;

	// move
	public float moveSpeed;
	static public bool m_dir = false;		// false : right, true : left
	static public bool m_move = false;

	// jump
	private float jumpSpeed;
	private Vector3 j_dir;
	static public bool m_jump = false;		// false : none, true : jump
	static public bool reclick = false;
	private float m_time;
	private float m_pos;

	private float t;
	private Vector3 dest;
	private float v;

	// object size
	private float halfsize_x;
	private float halfsize_y;

	void Start()
	{
		// move time : 1.0f / jump time : 0.7f
		moveSpeed = 450.0f / 1.0f;
		jumpSpeed = 130.0f / 0.7f;

		halfsize_x = 25.0f;
		halfsize_y = 45.0f;

		t = 0.7f;
		v = 130.0f / 0.7f;

		_transform = GetComponent<Transform> ();
	}

	void FixedUpdate ()
	{
		if( m_move == true )
			Move_Process ();

		Jump_Process ();
	}

	void Move_Process()
	{
		Vector3 dir = Vector3.zero;

		if( m_dir == false )
		{
			dir = new Vector3(1, 0, 0);
			dir.Normalize ();

			_transform.localPosition += dir * (moveSpeed * Time.fixedDeltaTime);
		}
		else if( m_dir == true )
		{
			dir = new Vector3(-1, 0, 0);
			dir.Normalize ();
			
			_transform.localPosition += dir * (moveSpeed * Time.fixedDeltaTime);
		}

		// 이동 제한
		_transform.localPosition = new Vector3 (Mathf.Clamp (_transform.localPosition.x, -640.0f + halfsize_x, 640.0f - halfsize_x),
		                                        Mathf.Clamp (_transform.localPosition.y, -360.0f + halfsize_y, 360.0f - halfsize_y),
		                                        _transform.localPosition.z);
	}

	float Jump_Calculate(float _t, float _start, float _a, float _d)
	{
		return -_a/2.0f * (Mathf.Cos(Mathf.PI*(Time.time-_t)/_d) - 1.0f) + _start;
	}

	void Jump_Process()
	{
		if( m_jump == true && reclick == false )
		{
			m_pos = _transform.localPosition.y;
			m_time = Time.time;
			dest = _transform.localPosition;
			j_dir = new Vector3(0, 1, 0);

			m_jump = false;
			reclick = true;
		}

		if( reclick == true )
		{
			_transform.localPosition +=
				j_dir * ((0.5f * jumpSpeed * (0.7f * 0.7f)) - (0.5f * (-Physics.gravity.y) * (0.7f * 0.7f)));
			jumpSpeed += Physics.gravity.y;
		}
				//j_dir * (jumpSpeed * Time.fixedDeltaTime);
	}

	void OnCollisionEnter2D( Collision2D other )
	{
		if( other.collider.tag == "Tile" )
		{
			jumpSpeed = 130.0f / 0.7f;
			reclick = false;
		}
	}
}