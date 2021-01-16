import 'dart:convert';
import 'dart:typed_data';

import 'package:android_remote/controller/mqtt_state.dart';
import 'package:get/get.dart';
import 'package:mqtt_client/mqtt_client.dart';
import 'package:mqtt_client/mqtt_server_client.dart';
import 'package:typed_data/typed_buffers.dart';

class MqttAdapter {
  // connection succeeded
  MqttServerClient client;
  final mqttState = Get.put(MqttState());

  void onConnected() {
    mqttState.updateClient(this.client);
    print('Connected');
  }

// unconnected
  void onDisconnected() {
    print('Disconnected');
  }

// subscribe to topic succeeded
  void onSubscribed(String topic) {
    print('Subscribed topic: $topic');
  }

  void publishMessage(String message) {
    Uint8List ascii = AsciiEncoder().convert(message);
    Uint8Buffer data = Uint8Buffer();
    data.addAll(ascii);
    mqttState.client.publishMessage('controller', MqttQos.atMostOnce, data);
  }

  connect(String host, int port, {String username, String password}) async {
    this.client = MqttServerClient.withPort(host, 'rama_android', port);
    this.client.logging(on: true);
    this.client.onConnected = onConnected;
    this.client.onDisconnected = onDisconnected;
    this.client.onSubscribed = onSubscribed;
    this.client.secure = false;
    final connMessage = MqttConnectMessage()
        // .authenticateAs(
        //     username == null ? "" : username, password == null ? "" : password)
        .withClientIdentifier('rama_android')
        .keepAliveFor(60)
        .startClean()
        .withWillQos(MqttQos.atMostOnce);
    this.client.connectionMessage = connMessage;
    try {
      await this.client.connect();
    } catch (e) {
      print('Exception: $e');
      this.client.disconnect();
    }
    // this.client .updates.listen(
    //   (List<MqttReceivedMessage<MqttMessage>> c) {
    //     final MqttPublishMessage message = c[0].payload;
    //     final payload =
    //         MqttPublishPayload.bytesToStringAsString(message.payload.message);
    //     print('Received message:$payload from topic: ${c[0].topic}>');
    //   },
    // );
  }
}
