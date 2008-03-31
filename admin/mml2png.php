#!/usr/bin/php

<?php

$mml2png = '/home/usr/jeuclid/bin/mml2xxx';
$ifontsize = '-FontSize 14.0';
$bfontsize = '-FontSize 18.0';

for ($i = 1; $i < $argc; $i++)
{
  print 'Converting mml to png in: ' . $argv[$i] . '
';  

  // Open input file
  $in = fopen($argv[$i], 'r');
  if ($in === false)
  {
    print 'Error opening: ' . $argv[$i] . '
';
    continue;
  }
    
  // Create a buffer to capture the output of the conversion process.
  ob_start();
  
  $n = 0;

  // For each line of the inpute file do:
  while (!feof($in))
  {
    $buffer = fgets($in);

    // Check for an opening math element.
    if (ereg('^<mml:math', $buffer))
    {
      $n++;
      $image = basename($argv[$i], '.html') . '.' . $n;
      $mmlfile = $image . '.mml';
      $pngfile = 'images/' . $image . '.png';

      // Inline or block?
      $inline = true;
      $fontsize = $ifontsize;
      if (ereg(' display="block"', $buffer))
      {
        $inline = false;
        $fontsize = $bfontsize;
      }
      // Open file for MathML
      $mml = fopen($mmlfile, 'w');

      // Write xml document declaration
      fwrite($mml, '<?xml version="1.0" encoding="UTF-8"?>
');

      while (!feof($in))
      {
        // Check for a closing math element
        // 
        if (ereg('</mml:math>', $buffer))
        {
          fwrite($mml, $buffer);
          fclose($mml);

          // Create image file
          exec($mml2png . ' ' . $mmlfile . ' ' . $pngfile . ' ' . $fontsize);

          // Include image in html.
          list($width, $height, $type, $attr) = getimagesize($pngfile);
           
          if ($inline)
          {
            $class = 'eqninlinemiddle';
            if ($height < 12)
              $class = 'eqninlinebottom';

            printf('<img class="%s" width="%d" height="%d" src="%s" />', 
                   $class, $width, $height, $pngfile);
          }
          else
          {
            printf('<p><img class="eqnblock" width="%d" height="%d" src="%s" /></p>',
                   $width, $height, $pngfile);
          }

          break;
        }
       
        fwrite($mml, $buffer);

        $buffer = fgets($in);
      }    
    }
    else
      echo $buffer;
  }

   
  // Close input file
  fclose($in);

  // Write the captured output to the output file.
  file_put_contents($argv[$i], ob_get_contents());

  // Close the buffer without flushing.
  ob_end_clean();

  if ($n != 0)
  {
    print 'Created ' . $n . ' images.
';
  }

}

?>
