<?php
?>

<div class="title">
     Screenshots
</div>


<?php

for($i=0;$i<11;$i++)
{


?>

<div class="ss_box">
     <div class="top"><!-- --></div>
     <div class="image_info_inactive" onmouseover="ssOver(this)" onmouseout="ssOut(this)">
          <div class="title">Particle System <?php echo $i; ?></div>
          <div class="date">2006-12-11 16:15:45</div>
     </div>
     <img src="gfx/ss_particles.png" alt="Particles Screenshot" />
     <div class="caption">
          Particle system in full effect. Better check that
          multi-lines work and all that.
     </div>
     <div class="bot"><!-- --></div>
</div>

<?php } ?>