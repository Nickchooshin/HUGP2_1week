using UnityEngine;
using System.Collections;

public class PatternManager : MonoBehaviour
{
	private bool first;

	void Start ()
	{
		first = false;

		// init
		// Pattern 1
		gameObject.GetComponent<Pattern1_1>().enabled = false;
		gameObject.GetComponent<Pattern1_2> ().enabled = false;
		gameObject.GetComponent<Pattern1_3> ().enabled = false;

		// Pattern 2
		gameObject.GetComponent<Pattern2_1> ().enabled = false;
		gameObject.GetComponent<Pattern2_2> ().enabled = false;
		gameObject.GetComponent<Pattern2_3> ().enabled = false;

		// Pattern 3
		gameObject.GetComponent<Pattern3_1> ().enabled = false;
		gameObject.GetComponent<Pattern3_2> ().enabled = false;
		gameObject.GetComponent<Pattern3_3> ().enabled = false;

		// Pattern 4
		gameObject.GetComponent<Pattern4_1> ().enabled = false;
		gameObject.GetComponent<Pattern4_2> ().enabled = false;

		// Pattern 5
		gameObject.GetComponent<Pattern5_1> ().enabled = false;
		gameObject.GetComponent<Pattern5_2> ().enabled = false;

		// Pattern 6
		gameObject.GetComponent<Pattern6_1> ().enabled = false;
		gameObject.GetComponent<Pattern6_2> ().enabled = false;

		Pattern_Turn ();
	}

	void FixedUpdate ()
	{
		if( true == Start_Count.start_check )
		{
			if( false == first )
			{
				gameObject.GetComponent<Pattern1_1>().enabled = true;
				first = true;
			}
			else
			{
				Pattern_Turn();
			}
		}
	}

	void Pattern_Turn()
	{
		if( true == Move_Character.m_dead )
			Application.LoadLevel ("End");

		// Pattern 1
		if (true == transform.GetComponent<Pattern1_1> ().end_check)
		{
			transform.GetComponent<Pattern1_1> ().end_check = false;
			gameObject.GetComponent<Pattern1_1>().enabled = false;
			gameObject.GetComponent<Pattern1_2>().enabled = true;
		}
		else if (true == transform.GetComponent<Pattern1_2> ().end_check)
		{
			transform.GetComponent<Pattern1_2> ().end_check = false;
			gameObject.GetComponent<Pattern1_2>().enabled = false;
			gameObject.GetComponent<Pattern1_3>().enabled = true;
		}
		else if (true == transform.GetComponent<Pattern1_3> ().end_check)
		{
			transform.GetComponent<Pattern1_3> ().end_check = false;
			gameObject.GetComponent<Pattern1_3>().enabled = false;
			gameObject.GetComponent<Pattern2_1>().enabled = true;
		}
		// Pattern 2
		else if (true == transform.GetComponent<Pattern2_1> ().end_check)
		{
			transform.GetComponent<Pattern2_1> ().end_check = false;
			gameObject.GetComponent<Pattern2_1>().enabled = false;
			gameObject.GetComponent<Pattern2_2>().enabled = true;
		}
		else if (true == transform.GetComponent<Pattern2_2> ().end_check)
		{
			transform.GetComponent<Pattern2_2> ().end_check = false;
			gameObject.GetComponent<Pattern2_2>().enabled = false;
			gameObject.GetComponent<Pattern2_3>().enabled = true;
		}
		else if (true == transform.GetComponent<Pattern2_3> ().end_check)
		{
			transform.GetComponent<Pattern2_3> ().end_check = false;
			gameObject.GetComponent<Pattern2_3>().enabled = false;
			gameObject.GetComponent<Pattern3_1>().enabled = true;
		}
		// Pattern 3
		else if (true == transform.GetComponent<Pattern3_1> ().end_check)
		{
			transform.GetComponent<Pattern3_1> ().end_check = false;
			gameObject.GetComponent<Pattern3_1>().enabled = false;
			gameObject.GetComponent<Pattern3_2>().enabled = true;
		}
		else if (true == transform.GetComponent<Pattern3_2> ().end_check)
		{
			transform.GetComponent<Pattern3_2> ().end_check = false;
			gameObject.GetComponent<Pattern3_2>().enabled = false;
			gameObject.GetComponent<Pattern3_3>().enabled = true;
		}
		else if (true == transform.GetComponent<Pattern3_3> ().end_check)
		{
			transform.GetComponent<Pattern3_3> ().end_check = false;
			gameObject.GetComponent<Pattern3_3>().enabled = false;
			gameObject.GetComponent<Pattern4_1>().enabled = true;
		}
		// Pattern 4
		else if (true == transform.GetComponent<Pattern4_1> ().end_check)
		{
			transform.GetComponent<Pattern4_1> ().end_check = false;
			gameObject.GetComponent<Pattern4_1>().enabled = false;
			gameObject.GetComponent<Pattern4_2>().enabled = true;
		}
		else if (true == transform.GetComponent<Pattern4_2> ().end_check)
		{
			transform.GetComponent<Pattern4_2> ().end_check = false;
			gameObject.GetComponent<Pattern4_2>().enabled = false;
			gameObject.GetComponent<Pattern5_1>().enabled = true;
		}
		// Pattern 5
		else if (true == transform.GetComponent<Pattern5_1> ().end_check)
		{
			transform.GetComponent<Pattern5_1> ().end_check = false;
			gameObject.GetComponent<Pattern5_1>().enabled = false;
			gameObject.GetComponent<Pattern5_2>().enabled = true;
		}
		else if (true == transform.GetComponent<Pattern5_2> ().end_check)
		{
			transform.GetComponent<Pattern5_2> ().end_check = false;
			gameObject.GetComponent<Pattern5_2>().enabled = false;
			gameObject.GetComponent<Pattern6_1>().enabled = true;
		}
		// Pattern 6
		else if (true == transform.GetComponent<Pattern6_1> ().end_check)
		{
			transform.GetComponent<Pattern6_1> ().end_check = false;
			gameObject.GetComponent<Pattern6_1>().enabled = false;
			gameObject.GetComponent<Pattern6_2>().enabled = true;
		}
		else if (true == transform.GetComponent<Pattern6_2> ().end_check)
		{
			transform.GetComponent<Pattern6_2> ().end_check = false;
			ScoreManager.getInstance().game_Clear = true;
			Application.LoadLevel ("End");
		}
	}
}