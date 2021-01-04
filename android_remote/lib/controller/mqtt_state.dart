import 'package:get/get.dart';
import 'package:mqtt_client/mqtt_server_client.dart';

class MqttState extends GetxController {
  MqttServerClient client;
  updateClient(MqttServerClient client) {
    this.client = client;
    update();
  }
}
