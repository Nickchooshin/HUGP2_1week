using UnityEngine;
using System.Collections;

public class Enemy3_1 : MonoBehaviour
{
	Transform _mytransform;
	GameObject _child;
	private Vector3 _now;
	public Vector3 _to;
	public Vector3 _to2;
	private Vector3 m_dir;

	RaycastHit2D hit;
	
	public float moveSpeed;
	public bool move_check = true;
	public bool dir_check = false;	// false : left, true : right
	private bool first;
	private bool tile_check;
	public float m_angle;
	private float m_size;
	public int stop;
	float _time;

	void Start ()
	{
		//dir_check = false;
		//move_check = false;
		first = false;
		tile_check = false;
		stop = 0;
		m_angle = 0.0f;
		m_size = 0.0f;
		_time = Time.fixedTime;

		_mytransform = GetComponent<Transform> ();
		_child = Instantiate (Resources.Load ("RayController", typeof(GameObject))) as GameObject;
		_child.transform.parent = GameObject.Find ("Boss").transform;
		_child.transform.localScale = new Vector3(10.0f, 10.0f, 0.0f);
		_child.transform.localPosition = _to;
		_now = _mytransform.transform.localPosition;

		if( true == dir_check )
			m_dir = new Vector3(_to.x + 160.0f, _to.y, _to.z) - _mytransform.transform.localPosition;
		else
			m_dir = new Vector3(_to.x, _to.y + 80.0f, _to.z) - _mytransform.transform.localPosition;

		moveSpeed = Mathf.Sqrt((m_dir.x * m_dir.x) + (m_dir.y * m_dir.y)) / 1.0f;
		_mytransform.transform.localScale = 
			new Vector3(_mytransform.transform.localScale.x, Mathf.Sqrt((m_dir.x * m_dir.x) + (m_dir.y * m_dir.y)), 0.0f);
		m_dir.Normalize ();

		if( true == dir_check )
			m_angle = Vector3.Angle (new Vector3(0.0f, -1.0f, 0.0f), m_dir);
		else
			m_angle = -Vector3.Angle (new Vector3(0.0f, -1.0f, 0.0f), m_dir);

		_mytransform.transform.localEulerAngles = new Vector3 (0.0f, 0.0f, m_angle);
			//_to - _mytransform.localPosition;
		//_child = gameObject.transform.FindChild ("RayController");
	}
	
	void FixedUpdate ()
	{
		if (true == move_check)
			Move ();
	}

	public void Move()
	{
		if( null != hit.collider )
			Move_Character.m_dead = true;

		if( 1 == stop )
		{
			hit = Physics2D.Raycast (_mytransform.position, _child.transform.position, 100);
			Debug.DrawRay (_mytransform.position, _child.transform.position, Color.red, 100);
			_mytransform.transform.localScale =
				new Vector3(_child.transform.localPosition.x - _now.x, _mytransform.transform.localScale.y, 0.0f);

			_child.transform.localPosition += m_dir * (moveSpeed * Time.fixedDeltaTime);
		}
		else if( 2 == stop )
		{
			moveSpeed = 300.0f / 1.0f;
			hit = Physics2D.Raycast (_mytransform.position, _child.transform.position, 100);
			Debug.DrawRay (_mytransform.position, _child.transform.position, Color.red, 100);
			if( true == dir_check )
			{
				m_angle = Vector3.Angle (new Vector3(0.0f, -1.0f, 0.0f), m_dir);
				m_dir = new Vector3(_child.transform.localPosition.x + 160.0f,
				                    _child.transform.localPosition.y,
				                    _child.transform.localPosition.z) - _mytransform.transform.localPosition;
			}
			else
			{
				m_angle = -Vector3.Angle (new Vector3(0.0f, -1.0f, 0.0f), m_dir);
				m_dir =
					new Vector3(_child.transform.localPosition.x,
					            _child.transform.localPosition.y + 80.0f,
					            _child.transform.localPosition.z) - _mytransform.transform.localPosition;
			}
			_mytransform.transform.localEulerAngles = new Vector3 (0.0f, 0.0f, m_angle);

			//_mytransform.transform.localScale =
			//	new Vector3(_child.transform.localPosition.x - _now.x, _mytransform.transform.localScale.y, 0.0f);

			if( false == dir_check )
			{
				if( _to2.x > _child.transform.localPosition.x )
					_child.transform.localPosition += new Vector3(1.0f, 0.0f, 0.0f) * (moveSpeed * Time.fixedDeltaTime);
			}
			else
			{
				if( _to2.x < _child.transform.localPosition.x )
					_child.transform.localPosition += new Vector3(-1.0f, 0.0f, 0.0f) * (moveSpeed * Time.fixedDeltaTime);
			}
		}
		else
		{
			hit = Physics2D.Raycast (_mytransform.position, _child.transform.position, 100);
			Debug.DrawRay (_mytransform.position, _child.transform.position, Color.red, 100);
		}
	}
}