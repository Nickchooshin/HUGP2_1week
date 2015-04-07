using UnityEngine;
using System.Collections;

public class Enemy3_1 : MonoBehaviour
{
	Transform _mytransform;
	public Vector3 _to;
	private Vector3 _to2;
	
	public float moveSpeed;
	public bool move_check = true;
	public bool dir_check = false;
	public float m_angle;

	void Start ()
	{
		//dir_check = false;
		//move_check = false;
		moveSpeed = 500.0f / 1.0f;
		m_angle = 0.0f;

		if (false == dir_check)
			_to2 = _to - new Vector3 (-5.0f, 0.0f, 0.0f);
		else
			_to2 = _to - new Vector3 (86.0f, 0.0f, 0.0f);

		_mytransform = GetComponent<Transform> ();
	}
	
	void FixedUpdate ()
	{
		if (true == move_check)
			Move ();
	}
	
	public void Move()
	{
		// Angle Setting
		Vector3 _from = new Vector3 (0.0f, -1.0f, 0.0f);
		_from.Normalize ();
		_to2.Normalize ();
		float _angle = Vector3.Angle (_from, _to2);

		if( false == dir_check )
			m_angle = -_angle;
		else
			m_angle = _angle;
		_mytransform.transform.eulerAngles = new Vector3 (0, 0.0f, m_angle);

		// Size Setting
		_mytransform.transform.localScale += _from * ((moveSpeed * 2.0f) * Time.fixedDeltaTime);
		_mytransform.transform.localPosition += _to2 * (moveSpeed * Time.fixedDeltaTime);
		_mytransform.GetComponent<BoxCollider2D>().size += 
			new Vector2(0.0f, moveSpeed * Time.fixedDeltaTime);
		//_collider.transform.localScale += new Vector3(0.0f, -1.0f, 0.0f) * ((moveSpeed * 2.0f) * Time.fixedDeltaTime);
		//Vector3 _dir = _mytransform.transform.localPosition - _finish;
		//_dir.Normalize ();

		//_mytransform.transform.localPosition += _dir * (moveSpeed * Time.fixedDeltaTime);
	}

	void OnColliderEnter2D( Collision2D other )
	{
		if( other.collider.tag == "Tile" )
		{
			move_check = false;
			Debug.Log("다롱");
		}
	}
}