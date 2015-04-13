using UnityEngine;
using System.Collections;

public class Enemy3_1 : MonoBehaviour
{
	Transform _mytransform;
	public Vector3 _to;
	public Vector3 _to2;
	private Vector2 draw_position;
	private Vector2 m_dir;

	Ray2D _ray;
	
	public float moveSpeed;
	public bool move_check = true;
	public bool dir_check = false;
	private bool first;
	private bool tile_check;
	public float m_angle;
	private float m_size;
	float _time;

	void Start ()
	{
		//dir_check = false;
		//move_check = false;
		first = false;
		tile_check = false;
		moveSpeed = 300.0f / 1.0f;
		m_angle = 0.0f;
		m_size = 0.0f;
		_time = Time.fixedTime;
		_ray = new Ray2D (Vector2.zero, Vector2.zero);

		if (false == dir_check)
			_to2 = _to - new Vector3 (-5.0f, 0.0f, 0.0f);
		else
			_to2 = _to - new Vector3 (86.0f, 0.0f, 0.0f);

		_mytransform = GetComponent<Transform> ();

		draw_position.x = _mytransform.transform.position.x;
		draw_position.y = _mytransform.transform.position.y;
	}
	
	void FixedUpdate ()
	{
		if (true == move_check)
			Move ();
	}
	
	public void Move()
	{
		// 셋팅
		Vector2 my_position;
		my_position.x = _mytransform.transform.position.x;
		my_position.y = _mytransform.transform.position.y;
		
		Vector2 end_position;
		end_position.x = _to.x;
		end_position.y = _to.y;

		Debug.Log("1 ="  + draw_position);
		Debug.Log("2 ="  + my_position);
		
		if( false == first )
		{
			m_dir = end_position - my_position;
			m_dir.Normalize();
			
			first = true;
			Debug.Log(Time.fixedTime - _time);
		}
		
		_ray = new Ray2D (my_position, m_dir);

		// 일반 이동
		RaycastHit2D hit = Physics2D.Raycast (my_position, draw_position);
		Debug.DrawRay (my_position, draw_position, Color.blue);

		if( false == tile_check )
		{
			draw_position += m_dir * ( moveSpeed * Time.fixedDeltaTime );
			//Debug.Log("2 ="  +  m_dir * ( moveSpeed * Time.fixedDeltaTime ));
		}
		// 땅에 닿았을 때 이동
		else
		{
			Vector2 dir = Vector2.zero;

			if( false == dir_check )
			{
				dir = new Vector2(1.0f, 0.0f);

				if( draw_position.x > _to2.x )
					draw_position += dir * ( moveSpeed * Time.fixedDeltaTime );
				else
					draw_position = new Vector2(_to2.x, draw_position.y);
			}
			else if( true == dir_check )
			{
				dir = new Vector2(-1.0f, 0.0f);

				if( draw_position.x < _to2.x )
					draw_position += dir * ( moveSpeed * Time.fixedDeltaTime );
				else
					draw_position = new Vector2(_to2.x, draw_position.y);
			}
		}

		if(hit.collider != null)
		{
			if( "Tile" == hit.collider.name )
				tile_check = true;

			Debug.Log(hit.collider.name);
		}
	}
}