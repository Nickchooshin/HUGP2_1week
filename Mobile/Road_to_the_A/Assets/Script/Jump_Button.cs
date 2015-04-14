using UnityEngine;
using System.Collections;

public class Jump_Button : MonoBehaviour
{
	void Click()
	{
		if( Move_Character.m_move == true && Move_Character.reclick == false )
		{
			Move_Character.m_jump = true;
		}
	}
}