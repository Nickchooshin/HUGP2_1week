using UnityEngine;
using System.Collections;

public class Back_Move : MonoBehaviour
{
	Transform _transform;
	public float moveSpeed;
	private float m_time;
	private bool m_dir;		// false : left, true : right

	void Start ()
	{
		m_dir = false;
		moveSpeed = 55.0f / 1.0f;
		m_time = Time.time;

		_transform = GetComponent<Transform> ();
	}

	void FixedUpdate ()
	{
		Vector3 dir = Vector3.zero;

		if( false == m_dir )
		{
			dir = new Vector3(1.0f, 0.0f, 0.0f);
			if( Time.time - m_time > 4.0f )
			{
				m_dir = true;
				m_time = Time.time;
			}
		}
		else
		{
			dir = new Vector3(-1.0f, 0.0f, 0.0f);
			if( Time.time - m_time > 4.0f )
			{
				m_dir = false;
				m_time = Time.time;
			}
		}
		
		_transform.localPosition += dir * (moveSpeed * Time.fixedDeltaTime);
	}
}