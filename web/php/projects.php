<?php
?>

<div class="title">
     Information
</div>

<div class="text">
   (Aboot projects) Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Proin dui turpis, semper ut, ornare vel, placerat sed, augue. Morbi sit amet magna sit amet enim nonummy dignissim. Duis tincidunt sollicitudin purus. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Morbi sed nulla. Duis elementum ultrices odio. In sed pede. Mauris tincidunt bibendum urna. Aliquam hendrerit odio at mauris. Integer leo est, malesuada sed, scelerisque at, mattis ut, lectus.
</div>
                            
<div class="title">
     Projects
</div>


<?php

for($i=0;$i<11;$i++)
{


?>

<div class="project">
     

  <div class="ss_box">
       <div class="top"><!-- --></div>
       <div class="image_info_inactive" onmouseover="ssOver(this)" onmouseout="ssOut(this)">
            <div class="title">Mega Game <?php echo $i; ?></div>
            <div class="date">2006-12-11 16:15:45</div> <br />
       </div>
       <img src="gfx/ss_particles.png" alt="Particles Screenshot" />
       <div class="caption">
            Particle system in full effect. Better check that
            multi-lines work and all that.
       </div>
       <div class="bot"><!-- --></div>
  </div>
  
     <div class="data">
          <div class="header">Mega Game!</div>
          <div class="author"> Mike Engar </div>
          <div class="date"> Novermber 5th, 2007 </div>

     <div class="textmenu">
	<div class="items">
		<a href="#"><div class="item" style="border-color: #ddd;"> + Download</div></a>
	</div>
     </div>

     </div>


<div class="breaker"><!-- --></div>
</div>  <!-- Project -->

<?php } ?>