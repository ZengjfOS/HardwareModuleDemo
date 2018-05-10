<?php header("Access-Control-Allow-Origin: *") ?>
<?php
    include 'functions.php';

    $data = json_decode(file_get_contents('php://input'), true);
    $categories = $data["categories"];
    $type = $data["type"];

    if ($categories == "network") {
        if ($type == "dhcp" || $type == "staticIP") {
            $networkFile = fopen("/etc/network/interfaces", "w+");
            $fileString = "";
            if ($type == "dhcp") {
                $fileString = "auto lo \niface lo inet loopback\n\n#dhcp \nauto eth0\niface eth0 inet dhcp\n";
            } elseif ($type == "staticIP"){
                $fileString = $fileString ."auto lo \niface lo inet loopback\n\n";
                $fileString = $fileString ."auto eth0\niface eth0 inet static\n";
                $fileString = $fileString ."    address ".$data["ip"]."\n";
                $fileString = $fileString ."    netmask ".$data["netmask"]."\n";
                $fileString = $fileString ."    broadcast ".$data["broadcast"]."\n";
                $fileString = $fileString ."    gateway ".$data["gateway"]."\n";
            } 
            fwrite($networkFile, $fileString);
            fclose($networkFile);
            
            echo '{"status": "ok"}';
            
            shell_exec('sync');
            shell_exec('reboot');
        }

        if ($type == "ping") {
            $IPOrDNS = $data["IPOrDNS"];
            $result = exec("ping -c 1 '".$IPOrDNS."' 2>&1 | grep '0% packet loss,'");
            if ($result != null)
                echo '{"status": "ok"}';
            else
                echo '{"status": "error"}';
        }
    }

    if ($categories == "dateAndTime" && $type == "dateAndTime") {
        $date = $data["date"];
        $time = $data["time"];

        $result = exec("date -s '".$date." ".$time."'");

        if (strpos($result, $time)){
            exec("hwclock -w");
            echo '{"status": "ok"}';
        } else {
            echo '{"status": "error"}';
        }

    }

    if ($categories == "MAC") {

        $eeprom_size = 256;
        $bytes = array();
        $bytes = array_pad($bytes, $eeprom_size, 0);

        $mac_address = $data["MAC"];
        $macArray = explode(':', $mac_address);
            
        $bytes[0] = 0x01;
        $bytes[1] = 0x06;
        $bytes[2] = hexdec($macArray[0]);
        $bytes[3] = hexdec($macArray[1]);
        $bytes[4] = hexdec($macArray[2]);
        $bytes[5] = hexdec($macArray[3]);
        $bytes[6] = hexdec($macArray[4]);
        $bytes[7] = hexdec($macArray[5]);
        $bytes[8] = 0x00;

        $bytes[0xfe] = 0x03;
        $bytes[0xff] = 0x00;


        $myfile = fopen("/sys/bus/i2c/devices/3-0050/eeprom", "wb");
        $i = 0;
        for (; $i < $eeprom_size; $i++) {
            fwrite($myfile, pack('C', $bytes[$i]));
        }

        fclose($myfile);

        if ($i == $eeprom_size) {
            echo '{"status": "ok", "MAC": "'.$mac_address.'"}';
        } else {
            echo '{"status": "error", "MAC": "'.$mac_address.'"}';
        }
    }

    if ($categories == "hardware_test") {
        $ret = `bin/buzzer /dev/buzzer&`;
        $output = `bin/hardware_test`;
        $json_array = json_decode($output, true);

        # check Micro SD is OK
        $result = exec("fdisk -l | grep /dev/mmcblk1:");
        if ($result != null)
            $json_array["data"]["MicroSD"]["status"] = "ok";
        else
            $json_array["data"]["MicroSD"]["status"] = "error";

        $json_array["data"]["MicroSD"]["name"] = "MicroSD";
        $json_array["data"]["MicroSD"]["index"] = 1;
        $json_array["data"]["MicroSD"]["descriptor"] = "network";
        $json_array["data"]["MicroSD"]["range"] = "";
        $json_array["data"]["MicroSD"]["value"] = "";

        /*
        $result = exec("ping -c 1 -W 1 ".$MiniOS->configs["hardware_test"]["network1"]["value"]." 2>&1 | grep ', 0% packet loss'");
        $json_array["network1_result"] = $result;
        if ($result != null)
            $json_array["data"]["network1"]["status"] = "ok";
        else
            $json_array["data"]["network1"]["status"] = "error";

        $json_array["data"]["network1"]["name"] = "network1";
        $json_array["data"]["network1"]["index"] = 1;
        $json_array["data"]["network1"]["descriptor"] = "network";
        $json_array["data"]["network1"]["range"] = "";
        $json_array["data"]["network1"]["value"] = "";

        $result = exec("ping -c 1 -W 1 ".$MiniOS->configs["hardware_test"]["network2"]["value"]." 2>&1 | grep ', 0% packet loss'");
        $json_array["network2_result"] = $result;
        if ($result != null)
            $json_array["data"]["network2"]["status"] = "ok";
        else
            $json_array["data"]["network2"]["status"] = "error";

        $json_array["data"]["network2"]["name"] = "network2";
        $json_array["data"]["network2"]["index"] = 1;
        $json_array["data"]["network2"]["descriptor"] = "network";
        $json_array["data"]["network2"]["range"] = "";
        $json_array["data"]["network2"]["value"] = "";
         */

        $json_array["status"] = "ok";
        echo json_encode($json_array);
    }
?>


