using UnityEngine;
using System.Collections;

public class Jump_Button : MonoBehaviour
{
	void Click()
	{
		Move_Character.m_jump = true;
	}
}