package database;


import java.io.InputStream;

import java.security.KeyStore;

import java.security.SecureRandom;
import java.security.cert.Certificate;
import java.security.cert.CertificateFactory;

import javax.net.ssl.SSLContext;
import javax.net.ssl.SSLSocketFactory;
import javax.net.ssl.TrustManagerFactory;
 
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;

import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttException;

import de.dcsquare.paho.client.util.Utils;
public class GestoreDB  implements Runnable{

	/*
	SSLContext sslContext = SSLContext.getInstance("SSL");
	TrustManagerFactory trustManagerFactory = TrustManagerFactory.getInstance(TrustManagerFactory.getDefaultAlgorithm());
	KeyStore keyStore = readKeyStore();
	trustManagerFactory.init(keyStore);
	sslContext.init(null, trustManagerFactory.getTrustManagers(), new SecureRandom());

	MqttConnectOptions options = new MqttConnectOptions();
	options.setSocketFactory(sslContext.getSocketFactory());
	 */
	private MqttClient mqttClient;
	public String topic;
	public String broker;


	public GestoreDB() throws Exception
	{
		topic = MainDB.TOPIC_SUB_DB;
		
		broker=MainDB.BROKER_CLOUD;
		//System.println(topic);
		//System.println(broker);
		String clientId = Utils.getMacAddress()+"wr-sub";
		
	

		MqttConnectOptions options = new MqttConnectOptions();
			SSLSocketFactory socketFactory = getSocketFactory("ca.crt");
		options.setSocketFactory(socketFactory);

		try
		{
			mqttClient = new MqttClient(broker, clientId);
		}
		catch (MqttException e)
		{
			e.printStackTrace();
			System.exit(1);
		}	

	}
	
	private static SSLSocketFactory getSocketFactory(String certificateName) throws Exception {
	      // Load the certificate from src/main/resources and create a Certificate object
	  		InputStream certStream = GestoreDB.class.getClassLoader().getResourceAsStream(certificateName);
	  		CertificateFactory certFactory = CertificateFactory.getInstance("X509");
	      Certificate certificate =  certFactory.generateCertificate(certStream);
	      SSLContext sslContext = SSLContext.getInstance("TLSv1.2");
	      TrustManagerFactory trustManagerFactory = TrustManagerFactory.getInstance(TrustManagerFactory.getDefaultAlgorithm());
	  		KeyStore keyStore = KeyStore.getInstance(KeyStore.getDefaultType());
	  		keyStore.load(null);
	  		keyStore.setCertificateEntry("alias", certificate);
	  		trustManagerFactory.init(keyStore);
	  		sslContext.init(null, trustManagerFactory.getTrustManagers(), new SecureRandom());
	  		return sslContext.getSocketFactory();
	    }

	/*private KeyStore readKeyStore() throws KeyStoreException, NoSuchAlgorithmException, CertificateException, IOException {
		KeyStore ks = KeyStore.getInstance("JKS");
		InputStream readCert = new FileInputStream("ca.crt");
		 try {
		        ks.load(readCert, "retilab");
		 } finally {
		        readCert.close();
		 }
			return ks;
	}*/

	/*public static SSLSocketFactory getSocketFactory(final String caCrtFile, final String crtFile, final String keyFile,
			final String password) {
		try {

			/**
			 * Add BouncyCastle as a Security Provider
			 */
	/*		Security.addProvider(new BouncyCastleProvider());

			JcaX509CertificateConverter certificateConverter = new JcaX509CertificateConverter().setProvider("BC");

			/**
			 * Load Certificate Authority (CA) certificate
			 */
	/*		PEMParser reader = new PEMParser(new FileReader(caCrtFile));
			X509CertificateHolder caCertHolder = (X509CertificateHolder) reader.readObject();
			reader.close();

			X509Certificate caCert = certificateConverter.getCertificate(caCertHolder);

			/**
			 * Load client certificate
			 */
	/*		reader = new PEMParser(new FileReader(crtFile));
			X509CertificateHolder certHolder = (X509CertificateHolder) reader.readObject();
			reader.close();

			X509Certificate cert = certificateConverter.getCertificate(certHolder);

			/**
			 * Load client private key
			 */
		/*	reader = new PEMParser(new FileReader(keyFile));
			Object keyObject = reader.readObject();
			reader.close();

			PEMDecryptorProvider provider = new JcePEMDecryptorProviderBuilder().build(password.toCharArray());
			JcaPEMKeyConverter keyConverter = new JcaPEMKeyConverter().setProvider("BC");

			KeyPair key;

			if (keyObject instanceof PEMEncryptedKeyPair) {
				key = keyConverter.getKeyPair(((PEMEncryptedKeyPair) keyObject).decryptKeyPair(provider));
			} else {
				key = keyConverter.getKeyPair((PEMKeyPair) keyObject);
			}

			/**
			 * CA certificate is used to authenticate server
			 */
	/*		KeyStore caKeyStore = KeyStore.getInstance(KeyStore.getDefaultType());
			caKeyStore.load(null, null);
			caKeyStore.setCertificateEntry("ca-certificate", caCert);

			TrustManagerFactory trustManagerFactory = TrustManagerFactory.getInstance(
					TrustManagerFactory.getDefaultAlgorithm());
			trustManagerFactory.init(caKeyStore);

			/**
			 * Client key and certificates are sent to server so it can authenticate the client
			 */
		/*	KeyStore clientKeyStore = KeyStore.getInstance(KeyStore.getDefaultType());
			clientKeyStore.load(null, null);
			clientKeyStore.setCertificateEntry("certificate", cert);
			clientKeyStore.setKeyEntry("private-key", key.getPrivate(), password.toCharArray(),
					new Certificate[]{cert});

			KeyManagerFactory keyManagerFactory = KeyManagerFactory.getInstance(
					KeyManagerFactory.getDefaultAlgorithm());
			keyManagerFactory.init(clientKeyStore, password.toCharArray());
			
			/**
			 * Create SSL socket factory
			 */
		/*	SSLContext context = SSLContext.getInstance("TLSv1.2");
			context.init(keyManagerFactory.getKeyManagers(), trustManagerFactory.getTrustManagers(), null);
			
			/**
			 * Return the newly created socket factory object
			 */
	/*		return context.getSocketFactory();

		} catch (Exception e) {
			e.printStackTrace();
		}

		return null;
	}*/

	public void sub() {
		try
		{
			mqttClient.setCallback(new GestoreDBCallback());
			mqttClient.connect();

			mqttClient.subscribe(topic);

			//System.println("GESTOREDB is now listening to "+topic);

		}
		catch (MqttException e) 
		{
			e.printStackTrace();
			System.exit(1);
		}

	}
	@Override
	public void run() {

		sub();
	}


}
