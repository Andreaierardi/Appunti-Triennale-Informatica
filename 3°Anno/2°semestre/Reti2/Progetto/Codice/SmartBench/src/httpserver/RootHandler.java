package httpserver;

import java.io.File;
import java.io.IOException;
import java.io.OutputStream;
import java.nio.file.Files;

import com.sun.net.httpserver.*;


public class RootHandler implements HttpHandler {

	@Override
	public void handle(HttpExchange he) throws IOException 
	{

		File index = new File("conf/config.html");
		he.sendResponseHeaders(200, index.length());
		OutputStream os = he.getResponseBody();
		Files.copy(index.toPath(), os);
		os.close();
	}		



}
