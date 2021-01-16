import 'package:android_remote/core/mqtt_adapter.dart';
import 'package:get/get.dart';
import 'package:mqtt_client/mqtt_server_client.dart';

class MqttState extends GetxController {
  MqttServerClient client;
  updateClient(MqttServerClient client) {
    this.client = client;
    update();
  }

  @override
  void onReady() {
    super.onReady();
    MqttAdapter().connect(
      '192.168.43.44',
      1883,
    );
  }
}
