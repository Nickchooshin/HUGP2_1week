using UnityEngine;
using System.Collections;

public class Safe4_1 : MonoBehaviour
{
	Transform _transform;
	private float m_speed;
	private Vector3 m_dir;
	public bool move_check;

	public AudioClip _sound;
	
	void Start ()
	{
		move_check = false;
		m_speed = 490.0f / 0.5f;
		move_check = false;
		m_dir = new Vector3 (-1.0f, 0.0f, 0.0f);

		_transform = GetComponent<Transform> ();
		
		GetComponent<AudioSource> ().clip = _sound;
		GetComponent<AudioSource> ().Play ();
	}
	
	void FixedUpdate ()
	{
		if (true == move_check)
			Move ();
	}

	void Move()
	{
		// Move
		_transform.transform.localPosition += m_dir * (m_speed * Time.fixedDeltaTime);

		if (_transform.transform.localPosition.x < -640.0f)
		{
			m_dir = new Vector3 (1.0f, 0.0f, 0.0f);
			m_speed = 790.0f / 0.5f;
		}
	}
}