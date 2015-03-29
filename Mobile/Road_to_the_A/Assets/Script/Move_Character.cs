using UnityEngine;
using System.Collections;

public class Move_Character : MonoBehaviour
{
	// transform
	Transform _transform;

	// move
	public float moveSpeed = 1.5f;
	static public bool m_dir = false;		// false : right, true : left
	static public bool m_move = false;

	// jump
	Vector3 j_dir = Vector3.zero;
	public float jumpSpeed = 7.0f;
	static public bool m_jump = false;		// false : none, true : jump
	static public bool reclick = false;

	// object size
	private float halfsize_x = 25.0f;
	private float halfsize_y = 45.0f;

	void Awake()
	{
		_transform = GetComponent<Transform> ();
	}

	void Update ()
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

			_transform.position += dir * moveSpeed * Time.deltaTime;
		}
		else if( m_dir == true )
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

	void Jump_Process()
	{
		if( m_jump == true && reclick == false )
		{
			j_dir = new Vector3(0, 1, 0);

			m_jump = false;
			reclick = true;
		}

		if( m_jump == false && reclick == true && j_dir.y > 0 )
			j_dir.Set(0, j_dir.y - 0.1f, 0);

		_transform.position += j_dir * jumpSpeed * Time.deltaTime;
	}

	void OnCollisionEnter2D( Collision2D other )
	{
		if( other.collider.tag == "Tile" )
		{
			reclick = false;
		}
	}
}