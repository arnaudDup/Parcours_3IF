package Protocole;

import java.net.InetAddress;
import java.util.HashMap;

public interface OnMessageReceived {
	public void todo(InetAddress Sender, HashMap<String,Object> message);
}
