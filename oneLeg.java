//the hight is defined to be 50mm (all Specifications are given in mm)

public class oneLeg {
    public oneLeg() {
        //length of the robot -----------------------------
        float length_a = 47; //Hüftgelenk
        float length_b = 58; //Knie
        float length_c = 85; //Fussgelenk

        //float length_robot = 132; //x-direction
        //float broad_robot = 56; //y-direction
        //Coordinates of the body -------------------------
        float body_x = 0;
        float body_y = 0;
        float body_z = 50;

        //ending point (back right) -----------------------
        float end_x = -50;
        float end_y = -80;
        float end_z = 0;

        //position vector ---------------------------------
        float a1 = end_x - body_x;
        float a2 = end_y - body_y;
        float amount_a = (float) Math.sqrt((a1 * a1) + (a2 * a2));

        //stretch factor ----------------------------------
        float stretch_factor = length_a / amount_a;

        //point A -----------------------------------------
        float a_x = a1 * stretch_factor;
        float a_y = a2 * stretch_factor;
        float a_z = body_z;

        //alpha -------------------------------------------
        float alpha = (float) Math.acos(a_x / length_a);
        float alpha_f = (float) Math.toDegrees(alpha);

        //AS-Vektor ---------------------------------------
        float as_x = a_x - end_x;
        float as_y = a_y - end_y;
        float as_z = a_z - end_z;
        float amount_as = (float) Math.sqrt((as_x * as_x) + (as_y * as_y) + (as_z * as_z));

        //gamma -------------------------------------------
        float gamma = (float) Math.acos((length_b * length_b + length_c * length_c - amount_as * amount_as) / (2 * length_b * length_c));
        float gamma_f = (float) Math.toDegrees(gamma);

        //---------------Beta------------------------------
        //beta1 -------------------------------------------
        float beta1 = (float) Math.acos((length_b * length_b + amount_as * amount_as - length_c * length_c) / (2 * length_b * amount_as));
        float beta1_f = (float) Math.toDegrees(beta1);

        //beta2 -------------------------------------------
        float length_boden = amount_a - length_a;
        float beta2 = (float) Math.atan(length_boden / body_z);
        float beta2_f = (float) Math.toDegrees(beta2);

        //beta --------------------------------------------
        float beta = 90 + beta1_f + beta2_f;

        //output -----------------------------------------
        System.out.println("Alpha = " + alpha_f);
        System.out.println("Beta = " + beta);
        System.out.println("Gamma = " + gamma_f);
    }

    public static void main(String[] args) {
        new oneLeg();
    }
 
}
