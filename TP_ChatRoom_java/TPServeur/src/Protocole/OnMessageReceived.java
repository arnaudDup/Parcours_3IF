package Protocole;

import java.net.InetAddress;
import java.util.HashMap;

public interface OnMessageReceived {
	public void todo(int UserID, HashMap<String,Object> message);
}
