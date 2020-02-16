package database;

public class Account {
	public String username;
	public String password;
	public String tipo;
	
	public Account(String usr, String pwd,String type)
	{
		username=usr;
		password=pwd;
		tipo=type;
	}
	public Account()
	{
		;
	}
	
	public String toString()
	{
		return("Username: " +username+" Password: "+ password+" Tipo:"+ tipo );
	}
}
