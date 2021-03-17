using System;
using System.Diagnostics;
using System.Reflection;
using System.Windows.Forms;
using Blend2D;

namespace Samples
{
    public partial class Form1 : Form
    {
        #region -- fileds --

        private int threadCount;

        #endregion -- fileds --

        #region -- constructor --

        public Form1()
        {
            InitializeComponent();

            Text = $"Blend2D - {GetAssemblyBuild()} - {GetPlatform()}";
        }

        #endregion -- constructor --

        #region -- control methods --

        private void Form_Load(object sender, EventArgs e)
        {
            comboBox1.SelectedIndex = 0;
            drawingControl.Label = label1;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            threadCount = comboBox1.SelectedIndex;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            drawingControl.DrawFunction = Sample1;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            drawingControl.DrawFunction = Sample2;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            drawingControl.DrawFunction = Sample3;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            drawingControl.DrawFunction = Sample4;
        }

        private void button5_Click(object sender, EventArgs e)
        {
            drawingControl.DrawFunction = Sample5;
        }

        private void button6_Click(object sender, EventArgs e)
        {
            drawingControl.DrawFunction = Sample6;
        }

        private void button7_Click(object sender, EventArgs e)
        {
            drawingControl.DrawFunction = Sample7;
        }

        private void button8_Click(object sender, EventArgs e)
        {
            drawingControl.DrawFunction = Sample8;
        }

        private void button9_Click(object sender, EventArgs e)
        {
            drawingControl.DrawFunction = Sample9;
        }

        private void button10_Click(object sender, EventArgs e)
        {
            drawingControl.DrawFunction = Sample10;
        }

        #endregion -- control methods --

        #region -- private methods --

        private void Sample1(BLImage image, BLRectI clip)
        {
            var context = new BLContext(image, new BLContextCreateInfo(threadCount));

            context.CompOp = BLCompOp.SourceCopy;
            context.FillAll();

            var path = new BLPath();
            path.MoveTo(26, 31);
            path.CubicTo(642, 132, 587, -136, 25, 464);
            path.CubicTo(882, 404, 144, 267, 27, 31);

            context.CompOp = BLCompOp.SourceOver;
            context.SetFillStyle(new BLRgba32(0xFFFFFFFF));
            context.FillPath(path);

            context.End();
        }

        private void Sample2(BLImage image, BLRectI clip)
        {
            var context = new BLContext(image, new BLContextCreateInfo(threadCount));

            context.CompOp = BLCompOp.SourceCopy;
            context.FillAll();

            var linear = new BLGradient(new BLLinearGradientValues(0, 0, 0, 480));
            linear.AddStop(0.0, new BLRgba32(0xFFFFFFFF));
            linear.AddStop(0.5, new BLRgba32(0xFF5FAFDF));
            linear.AddStop(1.0, new BLRgba32(0xFF2F5FDF));

            context.CompOp = BLCompOp.SourceOver;
            context.FillStyle = linear;
            context.FillRoundRect(40.0, 40.0, 400.0, 400.0, 45.5);
            context.End();
        }

        private void Sample3(BLImage image, BLRectI clip)
        {
            var context = new BLContext(image, new BLContextCreateInfo(threadCount));

            context.CompOp = BLCompOp.SourceCopy;
            context.FillAll();

            var pattern = new BLPattern(new BLImage("Resources\\Texture.jpeg"));

            context.CompOp = BLCompOp.SourceOver;
            context.FillStyle = pattern;
            context.FillRoundRect(40.0, 40.0, 400.0, 400.0, 45.5);
            context.End();
        }

        private void Sample4(BLImage image, BLRectI clip)
        {
            var context = new BLContext(image, new BLContextCreateInfo(threadCount));

            context.CompOp = BLCompOp.SourceCopy;
            context.FillAll();

            var pattern = new BLPattern(new BLImage("Resources\\Texture.jpeg"));

            context.Rotate(0.785398, 240.0, 240.0);

            context.CompOp = BLCompOp.SourceOver;
            context.FillStyle = pattern;
            context.FillRoundRect(50.0, 50.0, 380.0, 380.0, 80.5);
            context.End();
        }

        private void Sample5(BLImage image, BLRectI clip)
        {
            var context = new BLContext(image, new BLContextCreateInfo(threadCount));

            context.CompOp = BLCompOp.SourceCopy;
            context.FillAll();

            var radial = new BLGradient(new BLRadialGradientValues(180, 180, 180, 180, 180));
            radial.AddStop(0.0, new BLRgba32(0xFFFFFFFF));
            radial.AddStop(1.0, new BLRgba32(0xFFFF6F3F));

            context.CompOp = BLCompOp.SourceOver;
            context.FillStyle = radial;
            context.FillCircle(180, 180, 160);

            var linear = new BLGradient(new BLLinearGradientValues(195, 195, 470, 470));
            linear.AddStop(0.0, new BLRgba32(0xFFFFFFFF));
            linear.AddStop(1.0, new BLRgba32(0xFF3F9FFF));

            context.CompOp = BLCompOp.Difference;
            context.FillStyle = linear;
            context.FillRoundRect(195, 195, 270, 270, 25);
            context.End();
        }

        private void Sample6(BLImage image, BLRectI clip)
        {
            var context = new BLContext(image, new BLContextCreateInfo(threadCount));

            context.CompOp = BLCompOp.SourceCopy;
            context.FillAll();

            var linear = new BLGradient(new BLLinearGradientValues(0, 0, 0, 480));
            linear.AddStop(0.0, new BLRgba32(0xFFFFFFFF));
            linear.AddStop(1.0, new BLRgba32(0xFF1F7FFF));

            var path = new BLPath();
            path.MoveTo(119, 49);
            path.CubicTo(259, 29, 99, 279, 275, 267);
            path.CubicTo(537, 245, 300, -170, 274, 430);

            context.CompOp = BLCompOp.SourceOver;
            context.StrokeWidth = 15;
            context.StrokeStartCap = BLStrokeCap.Round;
            context.StrokeEndCap = BLStrokeCap.Butt;
            context.StrokeStyle = linear;
            context.StrokePath(path);

            context.End();
        }

        private void Sample7(BLImage image, BLRectI clip)
        {
            var context = new BLContext(image, new BLContextCreateInfo(threadCount));

            context.CompOp = BLCompOp.SourceCopy;
            context.FillAll();

            var face = new BLFontFace("Resources\\NotoSans-Regular.ttf");
            var font = new BLFont(face, 50.0f);

            context.FillStyle = new BLRgba32(0xFFFFFFFF);
            context.FillText(new BLPoint(60, 80), font, "Hello Blend2D!");
            context.Rotate(0.785398);
            context.FillText(new BLPoint(250, 80), font, "Rotated Text");
            context.End();
        }

        private void Sample8(BLImage image, BLRectI clip)
        {
            var context = new BLContext(image, new BLContextCreateInfo(threadCount));

            context.CompOp = BLCompOp.SourceOver;
            context.FillAll();

            var face = new BLFontFace("Resources\\NotoSans-Regular.ttf");
            var font = new BLFont(face, 20f);

            var fontMetrics = font.Metrics;
            var point = new BLPoint(20, 190 + fontMetrics.Ascent);
            var text = new string[] { "Hello Blend2D!",
                                      "I'm a simple multiline text example",
                                      "that uses BLGlyphBuffer and fillGlyphRun!",
                                      "Pi (\u03A0) and Sigma (\u03A3)." };

            var glyphBuffer = new BLGlyphBuffer();
            var textMetrics = default(BLTextMetrics);

            context.FillStyle = new BLRgba32(0xFFFFFFFF);

            foreach (var line in text)
            {
                glyphBuffer.SetText(line);
                font.Shape(glyphBuffer);
                font.GetTextMetrics(glyphBuffer, ref textMetrics);

                point.X = (480.0 - (textMetrics.BoundingBox.X1 - textMetrics.BoundingBox.X0)) / 2.0;
                context.FillGlyphRun(point, font, glyphBuffer.GlyphRun);
                point.Y += fontMetrics.Ascent + fontMetrics.Descent + fontMetrics.LineGap;
            }

            context.End();
        }

        private void Sample9(BLImage image, BLRectI clip)
        {
            var context = new BLContext(image, new BLContextCreateInfo(threadCount));

            context.CompOp = BLCompOp.SourceCopy;
            context.FillAll();

            var face = new BLFontFace("Resources\\NotoSans-Regular.ttf");
            var font = new BLFont(face, 75f);

            var glyphBuffer = new BLGlyphBuffer();
            var textMetrics = default(BLTextMetrics);
            var fontMetrics = font.Metrics;
            var text = "Text metrics";

            glyphBuffer.SetText(text);
            font.Shape(glyphBuffer);
            font.GetTextMetrics(glyphBuffer, ref textMetrics);

            var pos = new BLPoint(20.5, Math.Floor(fontMetrics.Ascent) + 180.5);

            context.StrokeStyle = new BLRgba32(0xFF905050);
            context.StrokeLine(pos.X, pos.Y - fontMetrics.Ascent, pos.X, pos.Y + fontMetrics.Descent);
            context.StrokeLine(pos.X, pos.Y, pos.X + textMetrics.Advance.X, pos.Y);

            context.FillStyle = new BLRgba32(0xFFFFFFFF);
            context.FillText(pos, font, text);

            context.FillStyle = new BLRgba32(0xFFFF9090);
            context.FillCircle(pos.X, pos.Y, 5);
            context.FillCircle(pos.X + textMetrics.Advance.X, pos.Y, 5);
        }

        private void Sample10(BLImage image, BLRectI clip)
        {
            var context = new BLContext(image, new BLContextCreateInfo(threadCount));

            context.CompOp = BLCompOp.SourceOver;
            context.FillAll();

            var face = new BLFontFace("Resources\\NotoSans-Regular.ttf");
            var font = new BLFont(face, 50.0f);
            var text = "Some sample text";

            var glyphBuffer = new BLGlyphBuffer();
            var glyphRun = default(BLGlyphRun);

            glyphBuffer.SetText(text);
            font.Shape(glyphBuffer);

            var styles = new MyStyle[] { new MyStyle(5, new BLRgba32(0xFFFFFFFF)),
                                         new MyStyle(5, new BLRgba32(0xFFFFFF00)),
                                         new MyStyle(6, new BLRgba32(0xFFFF0000)) };
            var index = 0u;
            var point = new BLPoint(30, 260);
            var placements = glyphBuffer.PlacementData;

            for (int styleId = 0; styleId < styles.Length; styleId++)
            {
                var style = styles[styleId];
                var size = style.Size;
                glyphBuffer.SetGlyphRun(ref glyphRun, BLGlyphPlacementType.AdvanceOffset, index, size);

                context.SetFillStyle(style.Color);
                context.FillGlyphRun(point, font, glyphRun);

                var end = index + size;
                var offset = new BLPoint();

                while (index < end)
                {
                    offset.X += placements[index].Advance.X;
                    offset.Y += placements[index].Advance.Y;
                    index++;
                }

                offset.X *= font.Matrix.M00;
                offset.Y *= font.Matrix.M11;
                point.X += offset.X;
                point.Y += offset.Y;
            }

            context.End();
        }

        private static string GetAssemblyBuild()
        {
            var assembly = Assembly.GetExecutingAssembly();

            foreach (var attribute in assembly.GetCustomAttributes(false))
            {
                var debuggableAttribute = attribute as DebuggableAttribute;

                if (debuggableAttribute != null && debuggableAttribute.IsJITTrackingEnabled)
                {
                    return "Debug";
                }
            }

            return "Release";
        }

        private static string GetPlatform()
        {
            if (UIntPtr.Size == 4)
            {
                return "x86";
            }

            return "x64";
        }

        #endregion -- private methods --

        private class MyStyle
        {
            #region -- properties --

            public uint Size
            {
                get;
            }

            public BLRgba32 Color
            {
                get;
            }

            #endregion -- properties --

            #region -- constructor --

            public MyStyle(uint size, BLRgba32 color)
            {
                Size = size;
                Color = color;
            }

            #endregion -- constructor --
        }
    }
}