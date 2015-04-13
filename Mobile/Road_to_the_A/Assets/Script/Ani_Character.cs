using UnityEngine;
using System.Collections;

public class Ani_Character : MonoBehaviour
{
	public AudioClip _DirSound;
	public AudioClip _JumpSound;
	public AudioClip _DeadSound;

	Transform _transform;
	public Animator _ani;
	private bool m_dir;

	private bool check;

	void Start ()
	{
		check = false;

		m_dir = Move_Character.m_dir;
		_transform = GetComponent<Transform> ();
		_ani = GetComponent<Animator> () as Animator;
	}

	void FixedUpdate ()
	{
		Set_Ani ();
	}

	void Set_Ani()
	{
		if (true == Move_Character.m_move)
		{
			if( false == check )
			{
				_ani.Play("Player_Walk");
				_ani.SetBool ("WALK", true);

				check = true;
			}
		}

		/*
		if( true == Move_Character.m_dead )
		{
			if( true == check )
			{
				_ani.Play("Player_Dead");
				_ani.SetBool ("WALK", false);
				_ani.SetBool ("DIR", false);
				_ani.SetBool ("JUMP", false);
				_ani.SetBool ("DEAD", true);
			}
		}
		*/
		if( m_dir != Move_Character.m_dir )
		{
			if( true == check )
			{
				_ani.Play("Player_Dir");
				_ani.SetBool ("DIR", true);
				_ani.SetBool ("WALK", false);
			}
		}
		else if (true == Move_Character.reclick)
		{
			if( true == check )
			{
				_ani.SetBool ("JUMP", true);
				_ani.SetBool ("WALK", false);
				_ani.Play("Player_Jump");
			}
		}
		else if (false == Move_Character.reclick)
		{
			if( true == check )
			{
				_ani.Play("Player_Walk");
				_ani.SetBool ("JUMP", false);
				_ani.SetBool ("WALK", true);
			}
		}
	}



	void Dir_Sound()
	{
		GetComponent<AudioSource> ().clip = _DirSound;
		GetComponent<AudioSource> ().Play ();
	}

	void Jump_Sound()
	{
		GetComponent<AudioSource> ().clip = _JumpSound;
		GetComponent<AudioSource> ().Play ();
	}
	
	void Dead_Sound()
	{
		GetComponent<AudioSource> ().clip = _DeadSound;
		GetComponent<AudioSource> ().Play ();
	}

	void Set_Dir()
	{
		if( false == Move_Character.m_dir )
			_transform.transform.eulerAngles = new Vector3 (0, 0.0f, 0);
		else
			_transform.transform.eulerAngles = new Vector3 (0, 180.0f, 0);

		m_dir = Move_Character.m_dir;
	}

	void Dir_Ani()
	{
		_ani.SetBool ("DIR", false);
		_ani.SetBool ("WALK", true);
	}
}