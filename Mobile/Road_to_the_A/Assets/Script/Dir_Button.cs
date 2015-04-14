using UnityEngine;
using System.Collections;

public class Dir_Button : MonoBehaviour
{
	void Click()
	{
		if( Move_Character.m_move == true )
		{
			if (Move_Character.m_dir == false)
				Move_Character.m_dir = true;
			else if (Move_Character.m_dir == true)
				Move_Character.m_dir = false;
		}
	}
}