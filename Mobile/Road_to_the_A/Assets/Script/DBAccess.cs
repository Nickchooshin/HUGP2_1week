
/*using UnityEngine;
using System;
using System.Collections;
using System.Data;
using Mono.Data.SqliteClient;

public class dbAccess : MonoBehaviour
{
	private string connection;
	private IDbConnection dbcon;
	private IDbCommand dbcmd;
	private IDataReader reader;
	
	// Use this for initialization
	void Start () {
		
	}
	
	public void OpenDB(string p)
	{
		connection = "URI=file:" + p; // we set the connection to our database
		dbcon = new SqliteConnection(connection);
		dbcon.Open();
	}
	
	public void CloseDB(){
		reader.Close(); // clean everything up
		reader = null;
		dbcmd.Dispose();
		dbcmd = null;
		dbcon.Close();
		dbcon = null;
	}
	
	IDataReader BasicQuery(string query){ // run a baic Sqlite query
		dbcmd = dbcon.CreateCommand(); // create empty command
		dbcmd.CommandText = query; // fill the command
		reader = dbcmd.ExecuteReader(); // execute command which returns a reader
		return reader; // return the reader
		
	}
	
	
	int CreateTable(string name,string[] col, string[] colType){ // Create a table, name, column array, column type array
		string query;
		query  = "CREATE TABLE " + name + "(" + col[0] + " " + colType[0];
		for(var i=1; i
		    query += ", " + col[i] + " " + colType[i];
		    }
		    query += ")";
		    try{
			dbcmd = dbcon.CreateCommand(); // create empty command
			dbcmd.CommandText = query; // fill the command
			reader = dbcmd.ExecuteReader(); // execute command which returns a reader
		}
		catch(Exception e){
			
			Debug.Log(e);
			return 0;
		}
		return 1;
		}
		
		int InsertIntoSingle(string tableName, string colName , string value ){ // single insert
			string query;
			query = "INSERT INTO " + tableName + "(" + colName + ") " + "VALUES (" + value + ")";
			try
			{
				dbcmd = dbcon.CreateCommand(); // create empty command
				dbcmd.CommandText = query; // fill the command
				reader = dbcmd.ExecuteReader(); // execute command which returns a reader
			}
			catch(Exception e){
				
				Debug.Log(e);
				return 0;
			}
			return 1;
		}
		
		int InsertIntoSpecific(string tableName, string[] col, string[] values){ // Specific insert with col and values
			string query;
			query = "INSERT INTO " + tableName + "(" + col[0];
			for(int i=1; i
			    query += ", " + col[i];
			    }
			    query += ") VALUES (" + values[0];
			    for(int i=1; i
			    query += ", " + values[i];
			    }
			    query += ")";
			    try
			    {
				dbcmd = dbcon.CreateCommand();
				dbcmd.CommandText = query;
				reader = dbcmd.ExecuteReader();
			}
			catch(Exception e){
				
				Debug.Log(e);
				return 0;
			}
			return 1;
			}
			
			int InsertInto(string tableName , string[] values ){ // basic Insert with just values
				string query;
				query = "INSERT INTO " + tableName + " VALUES (" + values[0];
				for(int i=1; i
				    query += ", " + values[i];
				    }
				    query += ")";
				    try
				    {
					dbcmd = dbcon.CreateCommand();
					dbcmd.CommandText = query;
					reader = dbcmd.ExecuteReader();
				}
				catch(Exception e){
					
					Debug.Log(e);
					return 0;
				}
				return 1;
				}
				
				public string[] SingleSelectWhere(string tableName , string itemToSelect,string wCol,string wPar, string wValue){ // Selects a single Item
					string query;
					query = "SELECT " + itemToSelect + " FROM " + tableName + " WHERE " + wCol + wPar + wValue;	
					dbcmd = dbcon.CreateCommand();
					dbcmd.CommandText = query;
					reader = dbcmd.ExecuteReader();
					string[] readArray = new string[reader.RecordsAffected];
					int i=0;
					while(reader.Read()){
						readArray[i]=reader.GetString(0); // Fill array with all matches
						i++;
					}
					return readArray; // return matches
				}
				
				
				
				
				
				// Update is called once per frame
				void Update () {
					
				}
				}
				*/